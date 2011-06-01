#!/usr/bin/racket
#lang racket

(require "./brute.rkt")

(define url-to-try #f)
(define file-to-try #f)
(define pattern-to-try #f)
(define passwd-first? #t)

(define hacking-options
  (command-line
   #:program "brute forcing url"
   #:once-each
   [("-u" "--url") url
    "Url to post the login/pass. Pass ~a in the name and url. Ex: http://www.xxx.com/login?login_theme=cpanel&user=~a&pass=~a"
    (set! url-to-try url)]
   [("-f" "--passwd-file") file-location
    "File with the format name:passwd. Ex:user:12346"
    (set! file-to-try file-location)]
   [("-p" "--fail-pattern") fail-pattern
    "Pattern to search the return to see if it was a fail. Ex: Failed!!"
    (set! pattern-to-try fail-pattern)]
   [("-w" "--passwd first?")
    "Use the passwd in the first position?"
    (set! passwd-first? #t)]
   #:args ()
   (if (not file-to-try)
      (displayln "File location not given.")
      (force-it! url-to-try file-to-try pattern-to-try passwd-first?))))
