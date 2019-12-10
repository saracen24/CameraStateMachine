//!
//! \file camera_state_machine.hpp.
//! \brief Camera state machine.
//! \author Aiz (c).
//! \date 2019.
//!

#pragma once
#ifndef CAMERA_STATE_MACHINE_HPP
#define CAMERA_STATE_MACHINE_HPP

namespace capture {

//!
//! \brief CameraStateMachine class.
//!
class CameraStateMachine {
 public:
  explicit CameraStateMachine() noexcept;
  //! NonCopyable.
  CameraStateMachine(const CameraStateMachine&) = delete;
  CameraStateMachine(CameraStateMachine&&) = delete;
  CameraStateMachine& operator=(const CameraStateMachine&) = delete;
  CameraStateMachine& operator=(CameraStateMachine&&) = delete;
  virtual ~CameraStateMachine() noexcept;

  void open();
  void start();
  void pause();
  void resume();
  void stop();
  void close();

  [[nodiscard]] bool isReady() const noexcept;
  [[nodiscard]] bool isCapture() const noexcept;
  [[nodiscard]] bool isPause() const noexcept;

 protected:
  virtual bool onOpen() = 0;
  virtual bool onStart() = 0;
  virtual bool onPause() = 0;
  virtual bool onResume() = 0;
  virtual bool onStop() = 0;
  virtual bool onClose() = 0;

 private:
  //!
  //! \brief State base class.
  //!
  class State {
   public:
    virtual ~State() noexcept = default;

    virtual bool open(CameraStateMachine*);
    virtual bool start(CameraStateMachine*);
    virtual bool pause(CameraStateMachine*);
    virtual bool resume(CameraStateMachine*);
    virtual bool stop(CameraStateMachine*);
    virtual bool close(CameraStateMachine*);

   protected:
    explicit State() noexcept = default;
  };

  //!
  //! \brief Change current state.
  //! \param[in] state New state.
  //!
  void change(State* state);

  //!
  //! \brief Off state class.
  //!
  class Off : public State {
   public:
    explicit Off() noexcept = default;
    ~Off() noexcept final = default;

    bool open(CameraStateMachine* csm) final;
  };

  //!
  //! \brief Ready state class.
  //!
  class Ready : public State {
   public:
    explicit Ready() noexcept = default;
    ~Ready() noexcept final = default;

    bool start(CameraStateMachine* csm) final;
    bool close(CameraStateMachine* csm) final;
  };

  //!
  //! \brief Capture state class.
  //!
  class Capture : public State {
   public:
    explicit Capture() noexcept = default;
    ~Capture() noexcept final = default;

    bool pause(CameraStateMachine* csm) final;
    bool stop(CameraStateMachine* csm) final;
  };

  //!
  //! \brief Pause state class.
  //!
  class Pause : public State {
   public:
    explicit Pause() noexcept = default;
    ~Pause() noexcept final = default;

    bool resume(CameraStateMachine* csm) final;
    bool stop(CameraStateMachine* csm) final;
  };

  //! Current state.
  State* m_state;

  bool m_isReady = false;
  bool m_isCapture = false;
  bool m_isPause = false;
};

}  // namespace capture

#endif
