if( $args.Count -ne 2 ) {
    Write-Output "Skripta prihvata tacno 2 argumenta"
    exit 1
}

$dir1 = $args[0]
$dir2 = $args[1]

if( !( Test-Path $dir1 -PathType Container ) ) {
    Write-Output "Prvi parametar nije direktorijum"
    exit 2
}

if( !( Test-Path $dir2 -PathType Container ) ) {
    Write-Output "Drugi parametar nije direktorijum"
    exit 3
}

$ekstenzije = Get-ChildItem $dir1 -Recurse -File | foreach { if( $_.Extension -ne "" ) { return $_.Extension } } | Select-Object -Unique

$prosek = 0
$len = 0
$count = 0

$minProsek = 0
$minProsekExt = $ekstenzije[0]

$minLen = 0
$minLenExt = $ekstenzije[0]

$ekstenzije.ForEach( {
    
    $fajlovi = Get-ChildItem $dir1 -Filter "*$_" -Recurse -File

    foreach( $fajl in $fajlovi ) {
        $count++
        $len += $fajl.Length
    }

    $lenGB = $len / 1000000000
    $prosek = $lenGB / $count
    Write-Output "Ekstenzija: $_`tProsek: $($prosek)GB`tUkupno: $($lenGB)GB"

    if( $minProsek -gt $prosek ) {
        $minProsek = $prosek
        $minProsekExt = $_
    }

    if( $minLen -gt $len ) {
        $minLen = $len
        $minLenExt = $_
    }

    $prosek = 0
    $len = 0
    $count = 0
} )


$dirNameProsek = "PROSEK" + ( $minProsekExt.Replace(".", "").ToUpper() )
$dirNameMin = "MIN" + ( $minLenExt.Replace(".", "").ToUpper() )

if( !( Test-Path "$dir2\$dirNameProsek" -PathType Container ) ) {
    New-Item -Path $dir2 -Name $dirNameProsek -ItemType Directory > $null
}

if( !( Test-Path "$dir2\$dirNameMin" -PathType Container ) ) {
    New-Item -Path $dir2 -Name $dirNameMin -ItemType Directory > $null
}

$prosekFajlovi = Get-ChildItem $dir1 -Filter "*$minProsekExt" -Recurse -File
$minFajlovi = Get-ChildItem $dir1 -Filter "*$minLenExt" -Recurse -File

 echo $prosekFajlovi | foreach { 
    if( !$_.IsReadOnly ) {
        Copy-Item $_.FullName -Destination "$dir2\$dirNameProsek"
    }
}

 echo $minFajlovi | foreach { 
    if( !$_.IsReadOnly ) {
        Copy-Item $_.FullName -Destination "$dir2\$dirNameMin"
    }
}