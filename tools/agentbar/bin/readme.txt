makecert -ss CCAgentBar -n "CN=Test" -sv CCAgentBar.pvk -r CCAgentBar.cer
cert2spc CCAgentBar.cer CCAgentBar.spc

cabarc -s 6144 n CCAgentBar.cab CCAgentBar.inf CCAgentBar.ocx
signcode