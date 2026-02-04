
(cl:in-package :asdf)

(defsystem "my_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "uwb_type" :depends-on ("_package_uwb_type"))
    (:file "_package_uwb_type" :depends-on ("_package"))
  ))