pocketsphinx_continuous -inmic yes 2>/dev/null | tee -a history.log | egrep -v --line-buffered '^INFO:|^ERROR:'
