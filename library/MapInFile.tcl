if {$argc != 1} {
  error "Usage: $argv0 directory"
}

set MAP {
}

foreach file [glob -directory [lindex $argv 0] -type f *] {
  set fd [open $file]
  fconfigure $fd -encoding utf-8
  set data [read $fd]
  close $fd
  set fd [open $file w]
  fconfigure $fd -encoding utf-8
  puts $fd [string trim [string map $MAP $data]]
  close $fd
}
