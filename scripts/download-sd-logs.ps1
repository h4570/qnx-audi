. ("$($PSScriptRoot)/variables.ps1")
Copy-item  -Force -Recurse "$($sd_dir)/logs" -Destination "$($project_dir)/logs"