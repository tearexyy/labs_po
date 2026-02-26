# Лабораторная работа 1. Базовая работа с git.
## 1. Установка программы
   Была установлена программа **Git Bash** для ОС Windows с [сайта git](https://git-scm.com/).

## 2. Проверка версии
```
$ git --version
git version 2.53.0.windows.1
```
## 3. Вывод справки с помощью команды **git --help**
```
$ git --help
usage: git [-v | --version] [-h | --help] [-C <path>] [-c <name>=<value>]
         [--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
         [-p | --paginate | -P | --no-pager] [--no-replace-objects] [--no-lazy-fetch]
         [--no-optional-locks] [--no-advice] [--bare] [--git-dir=<path>]
         [--work-tree=<path>] [--namespace=<name>] [--config-env=<name>=<envvar>]
         <command> [<args>]

These are common Git commands used in various situations:

start a working area (see also: git help tutorial)
   clone      Clone a repository into a new directory
   init       Create an empty Git repository or reinitialize an existing one

work on the current change (see also: git help everyday)
   add        Add file contents to the index
   mv         Move or rename a file, a directory, or a symlink
   restore    Restore working tree files
   rm         Remove files from the working tree and from the index

examine the history and state (see also: git help revisions)
   bisect     Use binary search to find the commit that introduced a bug
   diff       Show changes between commits, commit and working tree, etc
   grep       Print lines matching a pattern
   log        Show commit logs
   show       Show various types of objects
   status     Show the working tree status

grow, mark and tweak your common history
   backfill   Download missing objects in a partial clone
   branch     List, create, or delete branches
   commit     Record changes to the repository
   merge      Join two or more development histories together
   rebase     Reapply commits on top of another base tip
   reset      Set `HEAD` or the index to a known state
   switch     Switch branches
   tag        Create, list, delete or verify tags

collaborate (see also: git help workflows)
   fetch      Download objects and refs from another repository
   pull       Fetch from and integrate with another repository or a local branch
   push       Update remote refs along with associated objects

'git help -a' and 'git help -g' list available subcommands and some
concept guides. See 'git help <command>' or 'git help <concept>'
to read about a specific subcommand or concept.
See 'git help git' for an overview of the system.
```
## 4. В текущей папке для создания новых директорий:
```
mkdir git_labs
cd git_labs
mkdir reports
```
В файловом проводнике были созданы **readme.md** и **lab1.md**.

## 5. git init - создание репозитория
`git init`

## 6. После добавления информации о себе в файлы **readme.md** и **lab1.md** был выполнен **initial commit**:
```
git add .
git commit -m "initial commit"

commit c6c72689537d6eeda8a17a6568422358ba68c8d9
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Fri Feb 6 14:48:24 2026 +0300

initial commit
```
## 7. Проверка изменений **git diff** и **git status**
```
Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (main)
$ git diff

Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (main)
$ git status
On branch main
nothing to commit, working tree clean
```
   Внесем изменения
```
$ git diff 
diff --git a/reports/lab1.md b/reports/lab1.md
index 0fe618d..1caed42 100644
--- a/reports/lab1.md
+++ b/reports/lab1.md
@@ -69,3 +69,16 @@ See 'git help git' for an overview of the system.
   git add .
   git commit -m "initial commit"
+
+Внесем изменения

$ git status
On branch main
Changes not staged for commit:
(use "git add <file>..." to update what will be committed)
(use "git restore <file>..." to discard changes in working directory)
      modified:   reports/lab1.md

no changes added to commit (use "git add" and/or "git commit -a")
```
- git diff показывает конкретные различия в файлах от последнего коммита  
- git status показывает какие файлы в репозитории были изменены в текущей ветке  (modified)

### Из файла **readme.md**:
```
Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (main)
$ git diff readme.md
```
## 8. В **readme.md** добавим изменение, которое не было закомичено
`$ git restore readme.md` - изменение пропало в файле

## 9. Удалим **readme.md**
```
$ git status
On branch main
Changes not staged for commit:
(use "git add/rm <file>..." to update what will be committed)
(use "git restore <file>..." to discard changes in working directory)
      deleted:    readme.md

no changes added to commit (use "git add" and/or "git commit -a")
```
`$ git restore readme.md` восстановил файл

## 10. Вывод имени ветки:
```
$ git branch
* main
```
### Создание ветки:
`git branch lab1`  
`git checkout lab1` - переключились на нее

   Если будут незакоммиченные изменения, переключиться не получится из-за риска потерять изменения в текущей ветке:
```
$ git checkout main
error: Your local changes to the following files would be overwritten by checkout:
reports/lab1.md
Please commit your changes or stash them before you switch branches.
Aborting
```
## 11. Произведем слияние веток:
```
$ git merge main
Updating fe3c59a..3cf4948
Fast-forward
reports/lab1.md | 94 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
1 file changed, 94 insertions(+)
```
## 12. **merge conflict**
Если одну и ту же строку изменить по-разному в двух ветках, а после попытаться их слить, будет ошибка:
```
$ git merge main
Auto-merging readme.md
CONFLICT (content): Merge conflict in readme.md
Automatic merge failed; fix conflicts and then commit the result.

   <<<<<<< HEAD
   Лабораторные работы по Современным технологиям программирования 2 сесместр
   =======
   Лабораторные работы по Современным технологиям программирования 1 курс
   >>>>>>> main
   выполнила: Мокренко Дарья 5130201/50302
```
## 13. Проверим различия между ветками:
`$ git diff lab1 main`

### Удалим **lab1**:
`$ git branch -d lab1`  
`Deleted branch lab1 (was 92a8a0f).`

## 14. Создание удаленного репозитория:
- `ssh-keygen` - генерация ssh-ключа
- `git remote add origin https://github.com/tearexyy/labs_po.git` - добавление удаленного репозитория
- `$ git push -u origin main` - загрузка изменений

## 15. **pull** - получаем изменения, сделанные в удаленном репозитории
`$ git pull`

## 16. Клонирование репозитория во временную папку
```
$  git clone https://github.com/tearexyy/labs_po.git
Cloning into 'labs_po'...
remote: Enumerating objects: 55, done.
remote: Counting objects: 100% (55/55), done.
remote: Compressing objects: 100% (28/28), done.
remote: Total 55 (delta 17), reused 52 (delta 16), pack-reused 0 (from 0)
Receiving objects: 100% (55/55), 7.52 KiB | 513.00 KiB/s, done.
Resolving deltas: 100% (17/17), done.
```
### После клонирования:
```
$ ls
labs_po/
```
## 17. **git fetch** - запрос обновлений из удаленного репозитория
```
$ git fetch
From https://github.com/tearexyy/labs_po
* [new branch]      2nd-branch -> origin/2nd-branch
```

## 18. Создание ветки и установка upstream
```
$ git push --set-upstream origin lab2-test
Enumerating objects: 12, done.
Counting objects: 100% (10/10), done.
Delta compression using up to 18 threads
Compressing objects: 100% (5/5), done.
Writing objects: 100% (6/6), 818 bytes | 272.00 KiB/s, done.
Total 6 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
remote:
remote: Create a pull request for 'lab2-test' on GitHub by visiting:
remote:      https://github.com/tearexyy/labs_po/pull/new/lab2-test
remote:
To https://github.com/tearexyy/labs_po.git
* [new branch]      lab2-test -> lab2-test
branch 'lab2-test' set up to track 'origin/lab2-test'.
```
## 19. **pull request** - запрос на слияние/отправка изменений на проверку
Для проверки измененных файлов со второй ветки был создан PR с веткой main.  
На GitHub можно отследить изменения, сравнить их с предыдущим коммитом и добавить комментарии. 

## 20. История коммитов **git log**
```
$ git log
commit ba8742806446aea09d3a3565d785fb8b550e634a (HEAD -> main, origin/main, origin/HEAD)
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Fri Feb 20 17:10:52 2026 +0300

   cpp

commit 1788c2b43a18026969ba466ed5f48b1194f507a6
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Fri Feb 20 16:36:22 2026 +0300

   branches

commit a1dfae8eca59e249eb376931384de24cf6c96b47 (origin/lab2-test)
Merge: b0883c7 39bcdcf
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Fri Feb 20 16:08:02 2026 +0300

   check

commit 39bcdcf2bfd874ae4661200f47d60630472cd656 (origin/2nd-branch)
Author: древесина армавир <95883822+tearexyy@users.noreply.github.com>
Date:   Fri Feb 20 16:03:39 2026 +0300

   Update readme.md group num

commit b0883c7de21a0dc89be98b370d7ba6b0c36aefed
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Thu Feb 19 00:32:06 2026 +0300

   remote rep

commit 3bfb2dd15be1e698dc2e7b28e4f406e39a2c1eb4
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Thu Feb 19 00:23:54 2026 +0300

   added rep

commit 92a8a0f68fbeb518a573733ff039b36e728cc618
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 23:33:18 2026 +0300

   merge

commit cc013dd7b005cb369461f0c07976da2cd0c31067
Merge: e9dcabb 1ee0a4d
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 23:32:12 2026 +0300

   merge resolving

commit e9dcabba635657e87bf80e4faea6b4b8de3470c5
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 23:25:58 2026 +0300

   to check merge conflict2

commit 1ee0a4dc79aad9f52f7d0d07860a68b65e6324b1
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 23:25:34 2026 +0300

   to check merge conflict

commit 3cf494852cc56af728dc2c5e280023b59b00c412
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 23:15:00 2026 +0300

   point 8

commit ec8fbe9992d3f0a60870a6f2d0bb39b1bccfbbbc
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 23:00:17 2026 +0300

   8 point

commit e04be78f504897188b4c187b999af476fec478b7
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 22:42:51 2026 +0300

   diff checkout

commit fe3c59a60e7c94421bdaf05a3317ce7c6a030d8c
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Wed Feb 18 22:19:20 2026 +0300

   merge checkout

commit 466e548e906b3c3f06b512180adc79e5ce65e842
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Fri Feb 6 15:27:04 2026 +0300

   point 3

commit 719cc972b7b0add261a2cde4d04c296f13b2af9a
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Fri Feb 6 15:07:29 2026 +0300

   added group number

commit c6c72689537d6eeda8a17a6568422358ba68c8d9
Author: tearexyy <d.v.mokrenko@gmail.com>
Date:   Fri Feb 6 14:48:24 2026 +0300

   initial commit
```
