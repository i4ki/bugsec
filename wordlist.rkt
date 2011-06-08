#lang racket

(provide wordlist-combination
         combination
         concatenate-credentials)

;; Generate a wordlist based on login file and password file.
;; login-file : path?
;; password-file : path?
;; -> void?
(define (wordlist-combination login-file password-file output)
  (define output-port (current-output-port))
  (when output
    (set! output-port (open-output-file output #:exists 'replace)))
  (define login-port (open-input-file login-file))
  (define pass-port (open-input-file password-file))
  
  (define comb (combination login-port pass-port))
  (displayln comb)
  comb)

;; generated a cartesian product of login x password
;; combination : input-port input-port -> (listof (pair string string))
(define (combination login-port pass-port)
  (let ([logins (port->lines login-port)]
        [pass   (port->lines pass-port)])
    (for*/list ([i logins]
                [j pass])
               (cons i j))))

(define (concatenate-credentials wlist)
  (let ([wordlist ""])
    (for/list ([nv wlist])
              (displayln nv)
              (set! wordlist (string-append wordlist
                                            (car nv)
                                            ":"
                                            (cdr nv)
                                            "\n")))
    wordlist))









