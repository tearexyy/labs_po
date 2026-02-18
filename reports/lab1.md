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

