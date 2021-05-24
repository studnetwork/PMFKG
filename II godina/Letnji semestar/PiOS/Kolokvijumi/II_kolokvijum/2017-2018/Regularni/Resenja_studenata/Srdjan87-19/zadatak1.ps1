if( $args.Count -ne 1 ) {
    Write-Output "Skripta prima tacno 1 parametar"
    exit 1
}

$putanja = $args[0]

if( !( Test-Path $putanja -PathType Leaf ) ) {
    Write-Output "Neispravna putanja"
    exit 2
}

$fajlovi = Get-ChildItem . -File

$notRO = @()
$roCount = 0
$notROCount = 0

$fajlovi.ForEach({
    if( $_.isReadOnly ) {
       $roCount++
    }
    else {
        if( (Get-Date).addMonths(-1) -le $_.CreationTime ) {
            $notRO += $_
        }
        $notROCount++
    }
})

Write-Output "Broj fajlova po isReadOnly statusu`n" > $putanja 

Write-Output "ReadOnly: False`nCount: $notROCount`n" >> $putanja 
Write-Output "ReadOnly: True`nCount: $roCount`n" >> $putanja 

Write-Output "Trenutni datum $(get-date -Format 'MM/dd/yyyy HH:mm:ss')" >> $putanja 
Write-Output "Fajlovi koji nisu readOnly a kreirani su u poslednjih mesec dana su:" >> $putanja 

Write-Output $notRO | Select-Object Name, Length, CreationTime >> $putanja 