# Pantheon Slack Integration

Ever wanted to deploy your [Pantheon](https://www.pantheon.io) site via Slack?

Well now you can using this handy middleware.

## Getting Started

1. Upload this site to a Pantheon site (or other hosting provider) you control.
2. Add you AES 256 private key to `../private/key.pmte` relative to the Drupal root directory.
3. Enable the following modules:
  * Chaos Tools
  * Entity Construction Kit
  * Encrypt
  * Features
  * Pantheon Slack Feature
  * Field encrypt
  * Composer Manager
  * Entity API
  * Secure Pages
  * Key
  * Key Encrypt
  * Pantheon Slack
4.  Add a custom [Slash Command](https://api.slack.com/slash-commands) via your Slack control panel.
5.  Change the `slack_slash_command_token` variable in Drupal to be the token you got in step 4 while creating your custom command.


## Contributing

This is a work in progress that is (mostly) functional.  Pull requests and Issues are always welcome.
