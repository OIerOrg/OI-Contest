LANG=zh . <(curl https://hydro.ac/setup.sh)
cpolar service start
rm -rf './backup'
mkdir -p './backup'
hydrooj backup
OUTPUT=$(ls -t | grep '^backup-' | head -n 1)

if [[ -z "$OUTPUT" ]]; then
    echo '未找到备份文件'
    exit 1
fi


echo "找到备份文件: $OUTPUT"  # 输出 OUTPUT 的值
split -b 10M $OUTPUT "./backup/backup-part"
rm $OUTPUT

