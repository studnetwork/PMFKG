if( $args.Count -ne 2 ) {
    Write-Host "Potebno je uneti tacno 2 parametra"
    exit 1
}

$folder = $args[0]
$naziv = $args[1].ToString()+".txt"

if( !(Test-Path -Path $folder) ) {
    Write-Host "Folder na putanji: " + $folder + " ne postoji"
}

$txtFajlovi = Get-ChildItem -path $folder -File | where { $_.Extension -eq ".txt" }

$txtFajlovi.foreach({
    Write-Output "" >> $folder\$naziv
    Write-Output $_.Fullname >> $folder\$naziv
    Write-Output "" >> $folder\$naziv
    Get-Content $_.Fullname >> $folder\$naziv
    Write-Output "" >> $folder\$naziv
})