if( $args.Count -ne 3 ) {
    Write-Host "Unesite 3 argumenta"
    exit 1
}

$folder = $args[0]
$str1 = $args[1].ToString() + ".txt"
$str2 = $args[2].ToString() + ".txt"

if( !( Test-Path -Path $folder ) ) {
    Write-Host "Folder na putanji:" + $folder + " ne postoji"
    exit 1;
}

dir $folder -Directory >> $str1
dir $folder -File >> $str2