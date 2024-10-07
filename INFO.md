# INFO

## GIT

#### Flow:
* Make changes, push to specified branch, create Pull Request, review changes, Merge to main branch, pull down main to get the latest version, copy to sub branch if necessary.

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
