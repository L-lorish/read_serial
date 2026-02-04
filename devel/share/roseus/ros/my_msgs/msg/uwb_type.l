;; Auto-generated. Do not edit!


(when (boundp 'my_msgs::uwb_type)
  (if (not (find-package "MY_MSGS"))
    (make-package "MY_MSGS"))
  (shadow 'uwb_type (find-package "MY_MSGS")))
(unless (find-package "MY_MSGS::UWB_TYPE")
  (make-package "MY_MSGS::UWB_TYPE"))

(in-package "ROS")
;;//! \htmlinclude uwb_type.msg.html


(defclass my_msgs::uwb_type
  :super ros::object
  :slots (_angle _distance ))

(defmethod my_msgs::uwb_type
  (:init
   (&key
    ((:angle __angle) 0.0)
    ((:distance __distance) 0.0)
    )
   (send-super :init)
   (setq _angle (float __angle))
   (setq _distance (float __distance))
   self)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; float64 _angle
    8
    ;; float64 _distance
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _angle
     (setq _angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _distance
     (setq _distance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get my_msgs::uwb_type :md5sum-) "f5a2ee2aaf541b354d2c44aa9ea8522e")
(setf (get my_msgs::uwb_type :datatype-) "my_msgs/uwb_type")
(setf (get my_msgs::uwb_type :definition-)
      "#uwb_type.msg

float64 angle
float64 distance

")



(provide :my_msgs/uwb_type "f5a2ee2aaf541b354d2c44aa9ea8522e")


