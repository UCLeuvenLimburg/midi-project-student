# Setup

## Creating Your Very Own Fork

Follow [this link](https://classroom.github.com/a/D59eXn9i) and pick your student ID from the list. If your ID is not in the list, send me a mail.

Clone your repo using the following command, replacing `<<URL>>` by the url of your fork
(omit the `<` and `>`).

```bash
# Clone your repo
$ git clone <<URL>> midi-project

# Enter the repository
$ cd midi-project

# Add upstream remote
$ git remote add upstream https://github.com/UCLeuvenLimburg/midi-project-student
```

**Do not dare downloading the code as a zip.** It is *known* that strange things
tend to happen to the laptops of those who dare violate this rule. You think those few students using Linux installed it on purpose? Think again.

Also, **do not clone your repository into a DropBox/OneDrive/Google Drive managed directory**. That's your one way ticket straight to FreeBSD.

## GitHub

On the [main repository's website](https://github.com/UCLeuvenLimburg/midi-project-student),
click the Watch button in order to receive notifications about updates.

When updates are made, you can pull them as follows (note that you should first commit/stash all your changes, otherwise git might complain):

```bash
$ git pull upstream master
```
