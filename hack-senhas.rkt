#!/usr/bin/racket
#lang racket

(require "./brute.rkt")
(require "./wordlist.rkt")

(define-syntax-rule (format-proxy proxy)
  (let ([p (regexp-split ":" proxy)])
    (if (> (length p) 1)
        (list "http" (first p) (second p))
        (list "http" (first p) 8118))))

(define-syntax-rule (add-proxy brute-opt proxy)
  (let ([proxylist (config-proxylist brute-opt)])
    (if (list? proxylist)
        (set-config-proxylist! brute-opt (append proxylist (list proxy)))
        (set-config-proxylist! brute-opt (list proxy)))))

(define brute-opt (config #f #f #f #f #f #f #f))

(define generate #f)
(define brute #f)
(define permutation #f)
(define login-file #f)
(define password-file #f)
(define output-file #f)

(define hacking-options
  (command-line
   #:program "brute forcing url"
   #:once-each
   
   [("-u" "--url") url
                   "Url to post the login/pass. Pass ~a in the name and url. Ex: http://www.xxx.com/login?login_theme=cpanel&user=~a&pass=~a"
                   (set-config-url! brute-opt url)]
   [("-f" "--passwd-file") file-location
                           "File with the format name:passwd. Ex:user:12346"
                           (set-config-passwd-file! brute-opt file-location)]
   [("-p" "--fail-pattern") fail-pattern
                            "Pattern to search the return to see if it was a fail. Ex: Failed!!"
                            (set-config-pattern-fail! brute-opt fail-pattern)]
   [("-w" "--passwd first?")
    "Use the passwd in the first position?"
    (set-config-passwd-first?! brute-opt #t)]
   [("-l" "--login") login
                     "File with the logins. One login per line. Should be used along -p and -g."
                     (set! login-file login)]
   [("-P" "--password") pass
                        "File with the passwords. Using this option in conjunction with -l and -g do a cartesian product of login x password."
                        (set! password-file pass)]
   [("-g" "--generate")
    "Generate wordlists. Should be used with -l and -p or -r."
    (set! generate #t)]
   [("-b" "--brute")
    "Brute force"
    (set! brute #t)]
   [("-o" "--output") file
                      "Output file for brute-force or wordlist generated."
                      (set! output-file file)]
   [("-v" "--verbose") "Run with verbose messages"
                       (set-config-verbose?! brute-opt #t)]
   [("-d" "--debug") "Option for debug of responses from the server."
                     (set-config-debug?! brute-opt #t)]
   [("-x" "--proxy") proxy
                     "Use the specified HTTP proxy (<proxyhost[:port]>). If the port number is not specified, it is assumed at port 8118."
                     (add-proxy brute-opt (format-proxy proxy))]
   [("-X" "--proxylist") proxylist
                         "Use this list of proxies. (<proxyhost[:port]>,<proxyhost[:port]>,...)"
                         (let ([proxies (regexp-split "," proxylist)])
                           (for/list ([proxy proxies])
                             (add-proxy brute-opt (format-proxy proxy))))]
   #:args ()
   (let ([port-to-use #f])
     (if generate
         (when (and login-file password-file) 
           (if (not brute)
               (wordlist-combination login-file password-file output-file)
               
               (let* ([wlist (wordlist-combination login-file password-file "t")]
                      [wordlist (concatenate-credentials wlist)]
                      [port-to-use (open-input-string wordlist)])
                 (displayln wordlist)
                 (force-it-with-port! brute-opt port-to-use))))
         (if (not (config-passwd-file brute-opt))
             (displayln "File location not given.")
             (force-it-with-port! brute-opt port-to-use))))))

