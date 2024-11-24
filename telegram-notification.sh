#!/bin/bash

# Переменная для типа стадии
STAGE_TYPE=$1
# Токен Telegram бота
BOT_TOKEN="7581559629:AAEZrFGih3arFFEEh7rI9V5VjGbLPgelj08"
# Идентификатор чата, куда отправляются уведомления
CHAT_ID="253116484"

# Небольшая задержка (опционально)
sleep 2

# Формирование сообщения в зависимости от статуса стадии
if [ "$CI_JOB_STATUS" == "success" ]; then
  MESSAGE="Стадия: $STAGE_TYPE \nJob: $CI_JOB_NAME завершена успешно.\nПроект: $CI_PROJECT_NAME\nPipeline: $CI_PROJECT_URL/pipelines\nJob: $CI_JOB_URL"
else
  MESSAGE="Стадия: $STAGE_TYPE \nJob: $CI_JOB_NAME завершилась с ошибкой!\nПроект: $CI_PROJECT_NAME\nPipeline: $CI_PROJECT_URL/pipelines\nJob: $CI_JOB_URL"
fi

# Отправка сообщения в Telegram с проверкой успешности
if curl -s -X POST "https://api.telegram.org/bot$BOT_TOKEN/sendMessage" -d chat_id=$CHAT_ID -d text="$MESSAGE"; then
  echo "Уведомление отправлено успешно"
else
  echo "Ошибка отправки уведомления"
fi
