pocketsphinx_continuous -inmic yes -logfn /dev/null | awk -v date="$(date +"%m-%d-%Y %r:")" '{print date,$0,".";fflush(stdout);}' | tee ./history.log
