# CI/CD Automation Script

Этот проект содержит скрипт для автоматической сборки и деплоя приложения с использованием CI/CD. Скрипт использует протокол SCP для копирования файлов на удаленный сервер и отправляет уведомления о статусе сборки через Telegram.

## Описание

1. **Удаленный деплой**: Скрипт автоматически копирует файлы из локальной директории на удаленный сервер с помощью SCP.
2. **Уведомления**: После выполнения CI/CD задачи скрипт отправляет уведомление в Telegram о статусе сборки (успех или ошибка).

## Требования

- **Бот в Telegram** для получения уведомлений. Получите `TELEGRAM_BOT_TOKEN` и `TELEGRAM_USER_ID`.
- **Удаленный сервер** с SSH доступом для деплоя.
- **CI/CD система**, такая как GitLab CI.

## Как использовать

1. **Настройте параметры** в скрипте:
   - `REMOTE_USER`: имя пользователя на удаленном сервере.
   - `REMOTE_HOST`: IP-адрес или доменное имя удаленного сервера.
   - `REMOTE_PORT`: порт SSH для подключения.
   - `REMOTE_DIR`: директория на удаленном сервере для размещения файлов.
   - `LOCAL_DIR_1`: локальная директория, содержащая файлы для копирования.
   - `TELEGRAM_BOT_TOKEN`: ваш токен для Telegram бота.
   - `TELEGRAM_USER_ID`: ID вашего пользователя в Telegram для отправки сообщений.

2. **Добавьте скрипт в CI/CD pipeline**:
   - Подключите скрипт в процесс сборки CI/CD для автоматизации деплоя и уведомлений.

## Пример использования

```bash
#!/bin/bash

# Параметры для SCP
REMOTE_USER="kim"
REMOTE_HOST="192.168.1.43"
REMOTE_PORT="3333"
REMOTE_DIR="/usr/local/bin"
LOCAL_DIR_1="/home/gitlab-runner/DO6_CICD-1/src/cat/s21_cat"

# Копирование файлов на удаленный сервер
scp -P "$REMOTE_PORT" -oStrictHostKeyChecking=no "$LOCAL_DIR_1" "$REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR"

# Проверка статуса CI/CD задачи
if [[ $CI_JOB_STATUS == 'success' ]]; then
    CI_JOB_STATUS="SUCCESS"
else
    CI_JOB_STATUS="FAILED"
fi

# Отправка уведомления в Telegram
TELEGRAM_BOT_TOKEN=""
TELEGRAM_USER_ID=""
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Author:+$CI_COMMIT_AUTHOR%0A%0AJob name: $CI_JOB_NAME%0A%0AStatus:+$CI_JOB_STATUS%0A%0AProject:+$CI_PROJECT_NAME"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
