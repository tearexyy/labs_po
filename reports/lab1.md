Лабораторная работа 1
1. Установка программы
   Была установлена программа Git Bash с сайта https://git-scm.com/ для ОС Windows.

2. Проверка версии
   Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (lab1)
   $ git --version
   git version 2.53.0.windows.1

3. Вывод справки с помощью команды git --help
   Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (lab1)
   $ git -- help
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

4. В текущей папке для создания новых директорий:
   git mkdir git_labs
   cd git_labs
   mkdir reports
   В файловом проводнике были созданы readme.md и lab1.md

5. git init - создание репозитория

6. После добавления информации о себе в файлы readme.md и lab1.md был выполнен initial commit:
   git add .
   git commit -m "initial commit"

   commit c6c72689537d6eeda8a17a6568422358ba68c8d9
   Author: tearexyy <d.v.mokrenko@gmail.com>
   Date:   Fri Feb 6 14:48:24 2026 +0300

   initial commit

7. Проверка изменений git diff и git status

   Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (main)
   $ git diff

   Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (main)
   $ git status
   On branch main
   nothing to commit, working tree clean

   Внесем изменения

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

   git diff показывает конкретные различия в файлах от последнего коммита
   git status показывает какие файлы в репозитории были изменены в текущей ветке(modified)

   Из файла readme.md:
   Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (main)
$ git diff readme.md

8. В readme.md добавим изменение, которое не было закомичено
   $ git restore readme.md - изменение пропало в файле

9. Удалим readme.md
   $ git status
   On branch main
   Changes not staged for commit:
   (use "git add/rm <file>..." to update what will be committed)
   (use "git restore <file>..." to discard changes in working directory)
         deleted:    readme.md

   no changes added to commit (use "git add" and/or "git commit -a")

   $ git restore readme.md восстановил файл

9. Вывод имени ветки:
   $ git branch
   * main

   Создание ветки:
   git branch lab1
   git checkout lab1 - переключились на нее

      Если будут незакоммиченные изменения, переключиться не получится из-за риска потерять изменения в текущей ветке:
      $ git checkout main
      error: Your local changes to the following files would be overwritten by checkout:
      reports/lab1.md
      Please commit your changes or stash them before you switch branches.
      Aborting

10. Произведем слияние веток:
   $ git merge main
   Updating fe3c59a..3cf4948
   Fast-forward
   reports/lab1.md | 94 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   1 file changed, 94 insertions(+)

11. merge conflict
   Если одну и ту же строку изменить по-разному в двух ветках, а после попытаться их слить, будет ошибка:

   $ git merge main
   Auto-merging readme.md
   CONFLICT (content): Merge conflict in readme.md
   Automatic merge failed; fix conflicts and then commit the result.

   ..<<<<<<< HEAD
   ..Лабораторные работы по Современным технологиям программирования 2 сесместр
   ..=======
   ..Лабораторные работы по Современным технологиям программирования 1 курс
   ..>>>>>>> main
   ..выполнила: Мокренко Дарья 5130201/50302

12. Проверим различия между ветками:
   $ git diff lab1 main

   удалим lab1:
   $ git branch -d lab1
   Deleted branch lab1 (was 92a8a0f).

13. Создание удаленного репозитория:
    ssh-keygen - генерация ssh-ключа
    git remote add origin https://github.com/tearexyy/labs_po.git - добавление удаленного репозитория
    $ git push -u origin main - загрузка изменений

14. pull - получаем изменения, сделанные в удаленном репозитории
    $ git pull

15. Клонирование репозитория во временную папку
   $  git clone https://github.com/tearexyy/labs_po.git
   Cloning into 'labs_po'...
   remote: Enumerating objects: 55, done.
   remote: Counting objects: 100% (55/55), done.
   remote: Compressing objects: 100% (28/28), done.
   remote: Total 55 (delta 17), reused 52 (delta 16), pack-reused 0 (from 0)
   Receiving objects: 100% (55/55), 7.52 KiB | 513.00 KiB/s, done.
   Resolving deltas: 100% (17/17), done.

   После клонирования:
   $ ls
   labs_po/

16. git fetch - синхронизация с удаленным репозиторием и показ изменений
   $ git fetch
   From https://github.com/tearexyy/labs_po
 * [new branch]      2nd-branch -> origin/2nd-branch


17. Создание ветки и установка upstream
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


