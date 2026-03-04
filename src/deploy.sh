#! bin/bash

REMOTE_USER="kim"
REMOTE_HOST="192.168.1.43"
#REMOTE_HOST="localhost"
REMOTE_PORT="3333"
REMOTE_DIR="/usr/local/bin"
LOCAL_DIR_1="/home/gitlab-runner/DO6_CICD-1/src/cat/s21_cat"
scp -P "$REMOTE_PORT" -oStrictHostKeyChecking=no "$LOCAL_DIR_1" "$REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR"
#fff
