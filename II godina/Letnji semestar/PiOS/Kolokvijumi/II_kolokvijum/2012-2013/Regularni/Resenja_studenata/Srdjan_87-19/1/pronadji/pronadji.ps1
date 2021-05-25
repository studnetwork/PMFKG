if( $args.Length -ne 2 ) {
    Write-Host "Skripta prihvata tacno 2 argumenta"
    exit 1
}

$folder = $args[0]
$naziv = $args[1].ToString().ToLower()

if( !( Test-Path -Path $folder ) ) {
    Write-Host "Dati folder ne postoji"
}

[int] $brPojavljivanja = 0

Get-ChildItem $folder -Recurse | foreach {

    $temp = ([string]$_.BaseName).ToLower()

    if( $naziv.CompareTo( $temp ) -eq 0 ) {
        $brPojavljivanja++;
    }
}