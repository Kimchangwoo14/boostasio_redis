$fbsFiles = Get-ChildItem -Path (Get-Item $PSScriptRoot).Parent.GetDirectories("Protocol").FullName -Recurse -Filter "*.fbs"

foreach ($fbs in $fbsFiles)
{
    Write-Host $fbs.FullName

    & $PSScriptRoot\flatc.exe --cpp --csharp -o $fbs.DirectoryName $fbs.FullName
}