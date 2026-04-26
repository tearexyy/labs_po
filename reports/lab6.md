# Лабораторная работа 6. Простые CI-CD пайплайны

## 1. Базовые хуки в Git на стороне клиента
- __pre-commit__ запускается перед созданием коммита, после ввода сообщения коммита, но до его сохранения. Может прервать операцию
- prepare-commit-msg запускается перед открытием редактора сообщения коммита, но после создания сообщения по умолчанию. Не может прервать операцию
- __commit-msg__ запускается после того, как пользователь ввел сообщение коммита и вышел из редактора (проверка формата или наличия запрещенных слов). Может прервать операцию
- __post-commit__ запускается после успешного создания коммита. Используется для уведомлений, логирования. Не может прервать операцию
- __pre-merge-commit__	запускается до создания merge-коммита. Может прервать операцию
- __pre-push__ запускается перед отправкой в удалённый репозиторий. Может прервать операцию

### Хуки
В папке .git/hooks был добавлен файл pre-commit с таким кодом (проверка на .env)
```
#!/bin/sh

files=$(git diff --cached --name-only --diff-filter=ACM) # получаем список всех добавленных в индекс файлов

[ -z "$files" ] && exit 0 # если файлы не добавлены

for f in $files; do
  case "$f" in
    .env|*/.env|*.env.*) # запет на имя файла
      echo ".env файл не может быть добавлен в репозиторий"
      exit 1
      ;;
  esac
done

exit 0
```
В терминале с помощью команды `chmod +x .git/hooks/pre-commit` необходимо сделать файл исполняемым.

Аналогично был создан файл commit-msg и сделан исполняемым `chmod +x .git/hooks/commit-msg`.
Добавлена проверка на то, чтобы сообщение коммита начиналось с заглавной буквы.
```
#!/bin/sh
MSG=$(cat "$1")

if [ -z "$MSG" ]; then
  echo "сообщение коммита не может быть пустым"
  exit 1
fi

FIRST_CHAR=$(echo "$MSG" | cut -c 1)
case "$FIRST_CHAR" in
  [A-Z])

    ;;
  *)
    echo "Сообщение должно начинаться с заглавной буквы"
    exit 1
    ;;
esac

exit 0
```
### Тестирование
В корневую папку проекта был добавлен файл .env.
Пробный коммит:
```
Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (report)
$ git add .env

Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (report)
$ git commit -m "env"
.env файл не может быть добавлен в репозиторий
```
```
Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (report)
$ git add .

Дарья Мокренко@DESKTOP-V1FLN27 MINGW64 ~/git_labs (report)
$ git commit -m "lab6"
Сообщение должно начинаться с заглавной буквы
```
## 2. Хуки Git на стороне сервера
Конвертировать Markdown-файл в html-файл можно с помощью Pandoc `sudo apt install pandoc`.
Был добавлен remote репозиторий.
Для создания html файла в клон-репозиторий необходимо добавить хук post-receive:
```
#!/bin/sh

while read oldrev newrev refname; do
    if [ "$refname" = "refs/heads/report6" ]; then
        cd "/c/Users/Дарья Мокренко/Desktop/hook_test"
        git checkout -f report6
        pandoc -s reports/lab6.md -o reports/lab6.html --metadata title="Lab 6"
        echo ">>> HTML updated: reports/lab6.html"
    fi
done

exit 0
```
`chmod +x .git/hooks/post-receive` - теперь хук исполняемый.
`git config receive.denyCurrentBranch updateInstead` - для того, чтобы файл обновлялся при загруженных изменениях.
`git push server report6` - пушим.  
![](screenshots/html.png)

## 3. Сборка с помощью CMake
### Основные понятия
__CMake__ — это система генерации файлов сборки.
|Команда|Функция|
|:------|:------|
|project()|Проект|
|add_executable()|Исполняемый файл|
|add_library()|Библиотека|
|target_link_libraries()|Линковка|
|target_include_directories()|Добавить пути|
|target_sources()|Исходники	|
|target_compile_options()|Опции компиляции|
|target_compile_definitions()|Макросы|
|add_subdirectory()|Подпроекты|
|find_package()|Внешние пакеты|
