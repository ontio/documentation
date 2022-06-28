# Anonymous Credential

In an anonymous credential scheme there are **three** participants: issuer, user(prover), verifier. 

Issuer creates a certificate to user which contains a list of user's attributes and issuer's signature(use BBS+ signature). This protocol is formally called **credential issuance protocol**.

The user who is in possession of that credential can selectively disclose some parts to some verifier. This protocol is formally called
**credential presentation protocol**.

## 1. Background

### BBS signature 
- Setup: generate a pairing-friendly curve G, and target group Gt, pairing func e: G x G -> Gt. 
- KeyGen: sk = (x), pk = (g^x).
- Sign(m): sig = g^{1/(x+mprime)}, where mprime = H(m).
- Verify(m, sig): check if e(pk * g^{H(m)}, g^sig) == e(g, g). -->

### 1.1  BBS+ signature
- *Setup*: group G1, G2, Gt. pairing function e: G1 x G2 -> Gt. G1 and G2 are both of order p. 

   common params: 
     - g1 is a generator of G1.
     
     - g2 is a generator of G2. 
     
     - HRand, h1, ..., hL are elements from G1. 

- *KeyGen*: sample x from uniform distribution on Zp, output sk = x, pk = g2^x. 

- *Sign(sk, m1, ..., mL)*: choose two random numbers `E` and `s` from Zp. Compute 
   `B = g1 * HRand^s * (h1^m1 * ... * hL^mL)`, then compute `A = B^{1/(E+x)}`. 
   The signature is (A, B, E, s).

- *Verify(pk, m1, ..., mL, sig)*: 
  decode `sig` as (A, B, E, s), and check if `e(A, g2^E * pk) == e(B, g2)` and if `B == g1 * HRand^s * (h1^m1 * ... * hL^mL)`. 
  
### 1.2 Non-Interactive Proof of Knowledge (PoK) protocol
In this subsection, we give an example of non-interactive proof of knowledge protocol which proves that the public key is  generated as specified in the BBS+ signature scheme. That is, `π = PoK{x: w = g2^x && _g2 = _g1^x}` which can be translated as the prover proves knowledge of `x` such that `g2^x = w` and `_g2 = _g1^x`. And `w, g2, _g1, _g2` are assumed to be public.

The protocol we give is a standard sigma protocol. It consists three steps, namely, **commit, challenge, response**. Sigma protocol is a interactive protocol and it can be modified to be a non-interactive zero knowledge proof by using the well-known **Fiat-Shamir heuristic**. And the proof π = {C, S}.

1. commitment(prover):
    ```go
    r = rand(Zp)

    t1 = g2^r

    t2 = _g1^r
    ```
2. proof(prover):
    ```go
    P = t1 || t2 || g2 || _g1 || w || _g2    //join them together in binary format

    C = hash_to_int(P)                       //C is challenge

    S = (r + C * x) mod p                    //response to verifier
    ```
3. verify(verifier):
    ```go
    _t1 = g2^S * w^(-c)

    _t2 = _g1^S * _g2^(-c)

    _P = _t1 || _t2 || g2 || _g1 || w || _g2

    _C = hash_to_int(_P)    

    // use C to compare with _C, which was calculated just now
    if C == _C {
        return true
    } else {
        return false
    } 
    ```

## 2. Setup of Issuer's key pair

Given an array of attribute's names `AttributeNames`, the issuer's key pair is generated as follows:

1. Sample a random element `x` from Zp, and compute `w = g2^x`.
2. Sample a random element `_g1` from G1. And compute  `_g2 = _g1^x`.
3. Generate non-interactive proof of knowledge `π = PoK{x: w = g2^x && _g2 = _g1^x} = (C, S)` according
 to [section 1.2](./anon_cred.md#12-non-interactive-proof-of-knowledge-pok-protocol) which we reproduce here.

    - `r` :  sample a random element r from Zp
    - `t1` : compute t1 = g2^r.
    - `t2` : compute t2 = _g1^r.
    - `C`  : C = H(t1 || t2 || g2 || _g1 || w || _g2)  
    - `S`  : S = (r + C * x) mod p

4. Sample an array of elements from G1 for `AttributeNames`. For each attribute in `AttributeNames`, compute `HAttrs[i] = random(G1)` 
5. Sample two random elements from G1: `HRand` and `HSk`.
6. Set issuer's public key `ipk = (w, _g1, _g2, π, HAttrs, AttributeNames, HRand, HSk)`, and private key `isk = x`.
7. Return **ipk** and **isk**.

The following snippets in golang gives the reference data structures for issuer's key pair.

```go
type IssuerSecretKey struct {
    x BigNum
}
```
```go
type IssuerPublicKey struct {
    AttributeNames []string
    HAttrs         []G1Point // one G1-element for one attribute
    HRand          G1Point   // a random G1 point 
    HSk            G1Point   // a random G1 point to encode user's secret key 

    w              G2Point   // element from G2  
    _g1            G1Point   // point of G1
    _g2            G1Point   // point of G1

    //PoK{x: w = g2^x && _g2 = _g1^x}
    C              BigNum    // challenge
    S              BigNum    // response
}
```
<!--
After issuer's setup, it makes `ipk` published, so public parameters has following addition content:

 - `ipk` : Issuer's public key
   - `w`
   - `_g1`
   - `_g2`
   - `π` = (`C`, `S`)
     - `C`
     - `S`
   - `AttributeName`
   - `HAttr`
   - `HRand`
   - `HSk`
   -->

## 3. Issuance protocol
The issuance protocol is an interactive protocol which consists of the following steps:
1) The issuer sends a random **nonce** to the user.

2) The user creates a **Credential Request** using the public key of the issuer, user secret, and the nonce as input.

   The request consists of a commitment to the user secret (can be seen as a public key) and a zero-knowledge proof
   of knowledge of the user secret key.

   The user sends the credential request to the issuer.

3) The issuer verifies the credential request by verifying the zero-knowledge proof
    
    If the request is valid, the issuer issues a credential to the user by signing the commitment to the secret key
    together with the attribute values and sends the credential back to the user

4) The user verifies the issuer's signature and stores the credential that consists of
    the signature value, a randomness used to create the signature, the user secret, and the attribute values.
    
In short, this can be summarized in the following diagram: 

       Issuer  ------------------------  Prover 
        
                 -- nonce(BigNum) --> 
            
                 <-- CredRequest ---
            
                 --- Credential ---> 

- CredRequest contains a commitment `Nym` to user's secret key which is of the form `HSk^(sk) ` and a zk-PoK of Nym. 

- Credential contains the BBS+ signature on attributes and Nym. 

### 3.1 Generate Credential Request

<!-- 
Issuer generates a nonce, which is a random big number with τ bits and sends it to user.

 - `n` : nonce, n = rand{BigNum(τ)}

-->
User will generate the credential request with attribute values and `nonce` as input. This is done as follows:
1. Sample a random element `sk` from Zp as user's master secret.
2. Compute `Nym = HSk^(sk)` as a commitment to user's master secret. 
3. Generate zero knowledge proof `π = PoK{sk: Nym = HSk^sk} = (C, S)` as illustrated in [section 1.2]() which we reproduce here.
     - Sample a random element `r` from Zp.
     - Compute `t1 = HSk^r`.
     - Compute challenge `C = H(t1 || HSk || Nym || nonce)`.
     - Compute response `S = (r + C * sk) mod p`.

The following snippets in golang gives the reference data structures for credential request.
```go
type CredRequest struct {
   Nym             G1Point  //commitment to user's master secret
   IssuerNonce     BigNum   //nonce 
   Attrs           []BigNum //user's attributes

   //PoK that Nym is constructed as in the issuance protocol
   // i.e. PoK{(sk): HSk^sk = Nym }
   C               BigNum   //challenge in Sigma-protocol
   S               BigNum   //response in Sigma-protocol
}
```

### 3.2 Issue credential 
After receiving credential request from user, issuer verify `π = (C, S)` and generates credential for user. 
The credential is generated using issuer's private key `isk` as follows:
1. Sample two random elements `e, s` from Zp.
2. Compute `B = g1 · HRand^s · Nym · MulAll(HAttrs[i]^(Attrs[i]))`
3. Compute `A = B^(1/(e+x))`.
4. Return credential `(A, B, e, s, Attrs)`

The following snippets in golang gives the reference data structures for credential.
```go
type Credential struct {
   A               G1Point
   B               G1Point
   e               BigNum
   s               BigNum
   Attrs           []BigNum
}
```

<!-- 
__Notice:__ This protocol is based on DAA+ protocol from [CDL16], some steps have been changed 
in order to satisfy our demands.

Roles:

- I - Issuer
- U - User
- V - Verifier(also an user)

Steps:

1. Issuer Setup
2. Issuance ( Issuer -> User )
3. Presentation ( Prover -> Verifier )

<!-- 1. Issuer Setup
2. Join Request
3. Join Proceed
4. Sign Request
5. Sign Proceed
6. Verify
7. Link 

Public Parameter:

 - `τ` : security parameter 
 - `e: G1 x G2 -> GT` : bilinear map defined on G1 and G2
 - `G1` `G2` `GT` : groups with pairing function defined, eg: __bn256__
 - `p`: prime order of bilinear group
 - `g1`: G1's generators
 - `h0` `h1` ... `hL`: elements from G1
 - `g2` : G2's generators

 - `H1:{0,1}* -> G1` : a hash function to map string to G1 element
 - `H: {0,1}* -> {0,1}τ` : a hash function to map string to Zp number

-->


## 4. Presentation protocol
In the presentation protocol, the prover tries to convince the verifier that he knows some secret input such that some predicate is true. A typical example of predicate is that 
the prover is *in possession of an anonymous credential*, and he can **selectively disclose** some attributes while hiding the other attributes.

Before we give the proving algorithm, we list the information that the prover has.

- User's secret key `sk` and its commitment `Nym`.
- Attribute values `attrs = (a1,...,aL)`
- BBS+ signature `(A, B, e, s)`
- extra input
    - `(D, I)`: attribute predicate, describe what attributes will be disclosed. If D[j]==1, I[j]=attrs[j]=aj, else I[j]=null
    <!--
    - `bsn`     : basename, a string to make signature different everytime
     - `n`       - nonce, with τ bit length -->

### 4.1. Proving algorithm
The selectively disclosure proof can be generated as follows: 

1. Randomize A: sample a random element `r1` from Zp*, and compute `A' = A^r1`. 
2. Compute `_A = A'^(−e) · B^r1, r3 = 1/r1`.
3. Sample an element `r2` from Zp.
4. Compute `B' = B^r1 · HRand^(-r2)`, `s' = s - r2·r3`.
5. Generate zero knowledge proof `π = PoK{ (sk, {ai}_hidden, e, r2, r3, s') }` such that  
    - `_A/B' = A'^(-e) · HRand^r2 ` and 
    - `g1 · MulAll(hi^ai_reveal) = (B')^r3 · HRand^(-s') · HSk^(-sk) · MulAll(hi^(-ai_hidden))`, and hi is a shorthand for HAttrs[i]. 
    
    This proof can be generated as follows.
     - `r_ai`   : for i belongs to _D(attributes not disclosed), means __D[i]==0__
     - `r_e`    : random from Zp
     - `r_r2`   : random from Zp
     - `r_r3`   : random from Zp
     - `r_s'`   : random from Zp
     - `r_sk`  : random from Zp
     - `E`      : E = HSk^r_sk
     - `t1`     : t1 = A'^r_e · HRand^r_r2 
     - `t2`     : t2 = (B')^r_r3 · HRand^r_s' · E^(-1) · MulAll(hi^r_ai)
     - `c'`     : c' = H(A', _A, B', nym, t1, t2, g1, HRand, h1, ... , hL, w)
     - `nonce`  : nonce, with τ bit length, randomly generated again
     - `c`      : c = H(nonce, c', (D, I))
     - `s_sk`  : s_sk = r_sk + c · sk
     - `s_ai`   : s_ai = r_ai - c · ai, for i belongs to _D(attributes not disclosed)
     - `s_e`    : s_e = r_e - c · e
     - `s_r2`   : s_r2 = r_r2 + c · r2
     - `s_r3`   : s_r3 = r_r3 + c · r3
     - `s_s'`   : s_s' = r_s' - c · s'
     - `π`      : {c, s_sk, {s_ai}, s_e, s_r2, s_r3, s_s', nonce}, i belong to _D

Output is `(A', _A, d, nym, π)`, where π = {c, s_sk, {s_ai}, s_e, s_r2, s_r3, s_s', nonce}

The following snippets in golang gives the reference data structures for zero-knowledge proof.

```go
type Proof struct {
    APrime             G1Point  // randomized credential signature values
    ABar               G1Point  // randomized credential signature values
    BPrime             G1Point  // randomized credential signature values

    /* challenge in sigma-protocol */
    ProofC             BigNum
    /* response in sigma-protocol */
    ProofSSk           BigNum
    ProofSE            BigNum
    ProofSR2           BigNum
    ProofSR3           BigNum
    ProofSSPrime       BigNum
    ProofSAttrs        []BigNum

    Nonce              BigNum   // nonce used to avoid replay attack
    Nym                G1Point  
}
```

### 4.2 Verification

Verifier has the following information as input:

 - `(A', _A, B', nym, π)` : from signer
 - `{c, s_sk, {s_ai}, s_e, s_r2, s_r3, s_s', nonce}` : parse π

The verification algorithm proceeds as follows: 
 1. Check if `A' != 1` in G1; if false, return `false`.
 2. check if `e(A', w) == e(_A, g2)`; if false, return `false`. _This is zk-PoK for __A__._
 3. Parse __π__ : `{c, s_sk, {s_ai}, s_e, s_r2, s_r3, s_s', nonce} <- π`; if failed, return `false`.
 4. `~t1` : ~t1 = A'^s_e · HRand^s_r2 · (_A/B')^(-c) . _This is zk-PoK for __e__, __r2__._
 5. `~t2` : (B')^s_r3 · HRand^s_s' · HSk^(-s_sk) · MulAll(hi^(-s_ai)) · (g1·MulAll(hi^ai))^(-c)
    - the i above, first MulAll( ) belongs to _D, where D[i]==0(false)
    - the i above, second MulAll( ) belongs to D, where D[i]==1(true)
    - This is ZKPoK for __r3__, __s'__, __gsk__, __ai__ of _D.
 6. `c'` : c' = H(nonce, H(A', _A, B', nym, ~t1, ~t2, g1, HRand, h1, ... , hL, w), (D, I))
 7. Check if `c == c'` : if false: return `false`. Otherwise return `true`.


## 5. References 
[CL02]. J. Camenisch and A. Lysyanskaya. A Signature Scheme with Efficient Protocols. SCN 2002. 

[CL04]. J. Camenisch and A. Lysyanskaya. Signature Schemes and Anonymous Credentials
from Bilinear Maps. Crypto 2004. 

[BBS04]. D. Boneh, X. Boyen, and H. Shacham. Short Group Signatures. Crypto 2004. 

[BBS+]. Man Ho Au, Willy Susilo, and Yi Mu. Constant-Size Dynamic k-TAA. SCN 2006. 

[CDL16]. Camenisch, Jan, Manu Drijvers and Anja Lehmann. Attestation Using the Strong Diffie Hellman Assumption Revisited, ECCV 2016.