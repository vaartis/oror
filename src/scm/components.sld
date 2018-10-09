(define-library (components)
  (import (scheme base)
          (srfi 99))
  (export
   graphics-component
   graphics-component?
   make-graphics-component
   graphics-component-filename

   transform-component
   transform-component?
   make-transform-component
   transform-component-x
   transform-component-x-set!
   transform-component-y)

  (begin
    (define-record-type graphics-component #t #t filename)

    (define-record-type transform-component #t #t (x) (y))))
