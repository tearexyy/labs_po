Лабораторная работа 2. Git Flow, Code Review.
1. В репозитории были созданы папки для лаботраторных работ по "Структурам данных".
    mkdir cpplabs
    cd cpplabs
    mkdir lab1
    Туда были помещены файлы лабораторной работы №1 по "Структурам данных".

2. .gitignore
    .gitignore - файл, который сообщает гиту о том, какие файлы он должен игнорировать. 
    .gitignore нужен для защиты файлов с конфиденциальной информацией а также для того, чтобы в удаленном репозитории не отображались файлы компиляции, временные файлы.
    Для игнорирования файла a.out внутри .gitignore лежит правило: *.out.

3. Запрет на push в ветку main.
   Чтобы защитить содержимое ветки main от возможных ошибок, необходимо сделать так, чтобы push в эту ветку мог осуществляться только через pull request, то есть можно было бы проверить изменения.
   Для этого на GitHub необходимо перейти в:
   1) настройки репозитория 
   2) настройки веток (branches) 
   3) add classic branch protection rule (установить правило для ветки) 
   4) Для ветки main установить защиту Require a pull request before merging
   
4. Проверка
   На ветке main вносим изменения, 
   Теперь при попытке сделать push на main git bash предупреждает:
   $ git push
    Enumerating objects: 7, done.
    Counting objects: 100% (7/7), done.
    Delta compression using up to 18 threads
    Compressing objects: 100% (4/4), done.
    Writing objects: 100% (4/4), 418 bytes | 418.00 KiB/s, done.
    Total 4 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
    remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
    remote: Bypassed rule violations for refs/heads/main:
    remote:
    remote: - Changes must be made through a pull request.
    remote:
    To https://github.com/tearexyy/labs_po.git
    5c6943f..4486310  main -> main

5. С проверочной ветки pr-test вносим изменения с помощью git push
