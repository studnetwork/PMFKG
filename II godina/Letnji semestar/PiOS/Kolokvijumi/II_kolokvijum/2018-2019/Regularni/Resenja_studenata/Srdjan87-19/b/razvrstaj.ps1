
if( $args.Count -ne 2 ) {
    Write-Output "Potrebno je uneti tacno 2 parametra"
    exit 1
}

$dir1 = $args[0]
$dir2 = $args[1]

if( !( Test-Path $dir1 -PathType Container ) ) {
    Write-Output "Prvi parametar nije ispravna putanja do direktorijuma"
    exit 2
}

if( !( Test-Path $dir2 -PathType Container ) ) {
    Write-Output "Drugi parametar nije ispravna putanja do direktorijuma"
    exit 3
}

if( ( Convert-Path $dir1 ) -eq ( Convert-Path $dir2 ) ) {
    Write-Output "Prvi i drugi parametar predstavljaju istu putanju"
    exit 4
}

$fajlovi = Get-ChildItem $dir1 -File

$index = 0

$prefix = "dat_"

$fajlovi.ForEach({
    $baseName = $_.BaseName
    $ext = $_.Extension

    if( $i++ -lt 10 ) {
        $newBaseName += "0"
    }

    $destDir = ""

    if( $_.Length -lt 1000 ) {
        if( !( Test-Path "$dir2\manji" -PathType Container ) ) {
            New-Item -ItemType Directory -Name "manji" -Path $dir2 > $null
        }
        $destDir = "manji"
    }
    elseif( $_.Length -lt 1000000 ) {
        if( !( Test-Path "$dir2\srednji" -PathType Container ) ) {
            New-Item -ItemType Directory -Name "srednji" -Path $dir2 > $null
        }
        $destDir = "srednji"
    }
    else {
        if( !( Test-Path "$dir2\veci" -PathType Container ) ) {
            New-Item -ItemType Directory -Name "veci" -Path $dir2 > $null
        }
        $destDir = "veci"
    }

    Copy-Item $_.FullName -Destination "$dir2\$destDir"
    Rename-Item "$dir2\$destDir\$baseName$ext" ($prefix + $i + $ext)
})

