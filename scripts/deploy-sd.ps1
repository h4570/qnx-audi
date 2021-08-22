. ("$($PSScriptRoot)/variables.ps1")
Get-ChildItem -Recurse -Path "$($project_dir)/bin" -Filter $args[0] | Copy-Item -Destination $sd_dir
