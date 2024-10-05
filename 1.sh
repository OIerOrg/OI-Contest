#!/bin/bash

BACKUP_DIR="./backup"
PREFIX="backup"
TIMESTAMP=$(date +"%Y-%m-%dT%H-%M")

sudo su - root -c "
rm -rf '$BACKUP_DIR'
mkdir -p '$BACKUP_DIR'
hydrooj backup
OUTPUT=\$(ls -t | grep '^$PREFIX-' | head -n 1)

if [[ -z \"\$OUTPUT\" ]]; then
    echo '未找到备份文件'
    exit 1
fi

echo \"找到备份文件: \$OUTPUT\"  # 输出 OUTPUT 的值
split -b 10M \$OUTPUT \$BACKUP_DIR/\${PREFIX}-part
rm \$OUTPUT
"

sudo su - codespace -c "
    git add .
    git commit -m 'Backup on $TIMESTAMP'
    git push
"