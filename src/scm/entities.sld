(define-library (entities)
  (import (scheme base)
          (srfi 99)
          (srfi 1)

          (components))
  (export
   entity
   player-entity

   find-entity-component)

  (begin
    (define-record-type entity #t #t (components))

    ;; Extract a particaluar component from an entity.
    ;;
    ;; .returns A component, if found, or #f if not.
    (define (find-entity-component entity component)
      (find (rtd-predicate component) (entity-components entity)))

    ;; The entity that the player's supposed to play as
    (define player-entity
      (make-entity (list (make-graphics-component "girl.png")
                         (make-transform-component 0 0))))))
