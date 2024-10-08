# INFO

## GIT

#### Flow:
* Start by pulling main branch and then creating a feature branch to work on.
  * git pull origin main, git checkout -b <feature/new-feature>
* Push to feature branch, create Pull Request, review, Merge to main, delete feature branch, pull main to get the latest version.
  * git push origin <feature/new-feature>, Pull Request (Github), check & resolve conflicts, Merge to main branch (Github), delete feature branch after successfull merge (Github), git pull origin main, create a new feature branch to work on.

### Some commands:
* git branch -r (list all remote branches).
* git branch (list local branches and show current).
* git checkout -b <new_branch> <origin/branch> (new local branch with upstream branch).
* git checkout <brach_name> (switch to a branch).
* git branch --delete <branchname> /delete local branch.
* git push origin <branch_name> /push to remote branch.
* git pull origin <branch_name> (pull from remote branch).
* git fetch origin (fetch the remote branches).
* git ls-files (list files in remote repository).

### Git history:
* git checkout <commit_hash> /temporarily checkout an earlier commit.
* git checkout <branch_name> /return back to the current version.
* git revert <commit_hash> /revert to older commit specified by it's hash.
* git push origin <branch_name> /push it to make it current.
* git reset --hard <commit_hash> /reset to a specified older commit.
* git push origin <brach_name> --force /force push it to current branch (NOT REVERSABLE).
