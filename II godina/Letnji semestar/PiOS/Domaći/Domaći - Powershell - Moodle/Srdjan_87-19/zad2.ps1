if( $args.Count -ne 1 ) {
    Write-Output "Skripta prihvata tacno 1 parametar"
    exit 1
}

$putanja = $args[0]

$fajlovi = Get-ChildItem . -File
$nonROinfo = "Ime`tVelicina`tDatum kreiranja`n"
$roNum = 0
$nonROnum = 0

foreach( $fajl in $fajlovi ) {
    if( $fajl.IsReadOnly ) {
        $roNum++
    }
    else {
        $nonROnum++
        $nonROinfo += $fajl.Name + "`t" + $fajl.Length + "`t" + $fajl.CreationTime + "`n"
    }
}

Write-Output "Broj ReadOnly fajlova: $roNum" > $putanja
Write-Output "Broj fajlova koji nisu ReadOnly: $nonROnum" >> $putanja
Write-Output $nonROinfo >> $putanja