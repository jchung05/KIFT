IP=$(curl ifconfig.me)
curl freegeoip.net/xml/$IP | grep "^	" | sed -e '1,1d' > location_data.log
say -f location
