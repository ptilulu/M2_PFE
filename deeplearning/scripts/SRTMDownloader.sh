#!/bin/bash

mkdir -p ../downloaded;

for i in 0{1..9} {10..72} ; do
  for j in 0{1..9} {10..24} ; do
    if test -f "../downloaded/srtm_${i}_${j}.zip"; then
      echo "[Found] http://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/srtm_${i}_${j}.zip"
      continue
    elif [[ `wget -S --spider "http://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/srtm_${i}_${j}.zip"  2>&1 | grep 'HTTP/1.1 200 OK'` ]]; then
      wget "http://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/srtm_${i}_${j}.zip" -P "../downloaded"
    else
      echo "[Not Found] http://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/srtm_${i}_${j}.zip"
    fi
  done
done
