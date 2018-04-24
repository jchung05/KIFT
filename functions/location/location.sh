IP=$(curl ifconfig.me)
curl freegeoip.net/xml/$IP | grep "^	" | sed -e '1,1d' | sed -i 's/\bPI\b.*\bValue:\b//' your_file > location_data.log
say -f location_data.log
