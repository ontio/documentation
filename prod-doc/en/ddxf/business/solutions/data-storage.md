# Solution for data storage provider

For detail and technology support, please contact Ontology dev team.

## 1. Enable data storage for resources

提供资源的具体信息，包括资源的元信息，以及数据的认证方、数据的价格（ONG）等, 平台方自己进行存储

##### [元数据模板](../../../framework/data-storage/README.md#)

```js
{
  @context: "http://schema.org",
  @type: Dataset,
  identifier: did:ont:xxxx....,
  name: sample data,
  description: "Just a sample for structured data", 
  keywords: "sample, structured",
  publisher: {
    @type: Person,
    identifier: did:ont:yyyy....,
    name: My Name,
    ...
  },
  datePublished: 2019-01-01T00:00:00Z,
  creator: {...},
  version: 1,
  expires: 2020-02-01T00:00:00Z,
  license: "http://example.license.com/v1",
  ...
}
```

##### 示例数据模板

```js
{
  certifier: "did:ont:AMz77J4iuHGmAdw7P9g1CZ7SoL996AdyxC",
  coin: "ONG",
  data:"a",
  dataId: "",
  desc: "test1",
  img: "",
  keywords: ["test1"],
  name: "test1",
  dataSource: "test1",
  ontid: "did:ont:ALfPq6XV9Pa6oDKENunPvwxxaMX8tBiJhA",
  price: 1,
  metadata: {
      @context: "http://schema.org",
      @type: Dataset,
      identifier: 'did:ont:xxxx....',
      name: sample data,
      description: "Just a sample for structured data", 
      keywords: "sample, structured",
      publisher: {
      @type: Person,
      identifier: 'did:ont:yyyy',
      name: My Name,
    },
    datePublished: 2019-01-01T00:00:00Z,
    creator: {...},
  version: 1,
  expires: 2020-02-01T00:00:00Z,
  license: "http://example.license.com/v1"
  }
}
```



## 2. Enable data storage runtime

