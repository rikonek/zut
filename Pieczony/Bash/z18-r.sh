#/bin/bash

echo "Zajetosc: " $(( $(du -ks /etc | cut -f1) - $(du -ksS /etc | cut -f1) )) "KB"

