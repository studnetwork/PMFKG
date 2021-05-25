if( $args.Count -lt 3 ) {
    Write-Output "Skripta prima minimalno 3 parametra"
    exit 1
}

$dir1 = $args[0]
$dir2 = $args[1]

if( !( Test-Path $dir1 -PathType Container ) ) { 
    Write-Output "Prvi parametar ne predstavlja putanju do nekog direktorijuma"
    exit 2
}

if( !( Test-Path $dir2 -PathType Container ) ) { 
    Write-Output "Drugi parametar ne predstavlja putanju do nekog direktorijuma"
    exit 3
}

if( (Convert-Path $dir1) -eq (Convert-Path $dir2) ) {
    Write-Output "Prvi i drugi ne mogu biti ista putanja"
    exit 4
}

for( $i=2; $i -lt $args.Count; $i++ ) {
    $fajlovi = Get-ChildItem -Path $dir1 -Filter *.$($args[$i]) -Recurse -File

    if( $fajlovi.Count -gt 0 ) {
        if( Test-Path $dir2\$($args[$i]) -PathType Container ) {
            Write-Output "Na putanji $dir2 vec postoji folder $($args[$i])"
            Remove-Item $dir2\$($args[$i]) -Recurse -Confirm
        }
        else {
            New-item -Path $dir2 -Name $($args[$i]) -ItemType Directory > $null

            foreach( $fajl in $fajlovi ) {
                Copy-Item $fajl.FullName -Destination $dir2\$($args[$i])
            }
        }
    }
}
