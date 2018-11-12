# Contributing
If you happen to find any issues, or have any cool ideas for the next amazing feature for Solo chain, please head over to the [Github](https://github.com/punicasuite/solo-chain) repo, and help us make Solo chain even better.

## Development Setup
To get Solo chain up and running on your local machine for development on Solo chain, you can:
- Clone down the github repo `git clone git@github.com:punicasuite/solo-chain.git`
- Install dependencies `yarn install`
- Compile installer `yarn dev`

This will install and compile all required dependencies and source code, and spin up a local server to host the local codebase at `localhost:9080`. As you make changes to the codebase in the `./src` folder, the application will update with hot reloading.

If you have any issues getting setup, please reach out in the Github issues, or directly on Discord.

## Contribution Guidelines

Please open a pull request with signed-off commits. We appreciate your help! You can also send your codes as emails to the developer mailing list. You're welcomed to join the Ontology mailing list or developer forum.

Please provide detailed submission information when you want to contribute code for this project. The format is as follows:

Header line: explain the commit in one line (use the imperative).

Body of commit message is a few lines of text, explaining things in more detail, possibly giving some background about the issue being fixed, etc.

The body of the commit message can be several paragraphs, and please do proper word-wrap and keep columns shorter than about 74 characters or so. That way "git log" will show things nicely even when it's indented.

Make sure you explain your solution and why you're doing what you're doing, as opposed to describing what you're doing. Reviewers and your future self can read the patch, but might not understand why a particular solution was implemented.

Reported-by: whoever-reported-it Signed-off-by: Your Name youremail@yourhost.com
