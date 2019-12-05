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
  explicit CameraStateMachine();
  virtual ~CameraStateMachine();

  void open();
  void start();
  void pause();
  void resume();
  void stop();
  void close();

  bool isReady() const noexcept;
  bool isCapture() const noexcept;
  bool isPause() const noexcept;

 protected:
  virtual bool onOpen() = 0;
  virtual bool onStart() = 0;
  virtual bool onPause() = 0;
  virtual bool onResume() = 0;
  virtual bool onStop() = 0;
  virtual bool onClose() = 0;

 private:
  //! NonCopiable.
  CameraStateMachine(const CameraStateMachine&) = delete;
  CameraStateMachine& operator=(const CameraStateMachine&) = delete;

  //!
  //! \brief State base class.
  //!
  class State {
   public:
    virtual ~State() = default;

    virtual bool open(CameraStateMachine* const);
    virtual bool start(CameraStateMachine* const);
    virtual bool pause(CameraStateMachine* const);
    virtual bool resume(CameraStateMachine* const);
    virtual bool stop(CameraStateMachine* const);
    virtual bool close(CameraStateMachine* const);

   protected:
    explicit State() = default;
  };

  //!
  //! \brief Change current state.
  //! \param[in] state New state.
  //!
  void change(State* const state);

  //!
  //! \brief Off state class.
  //!
  class Off : public State {
   public:
    explicit Off() = default;
    virtual ~Off() override final = default;

    virtual bool open(CameraStateMachine* const csm) override final;
  };

  //!
  //! \brief Ready state class.
  //!
  class Ready : public State {
   public:
    explicit Ready() = default;
    virtual ~Ready() override final = default;

    virtual bool start(CameraStateMachine* const csm) override final;
    virtual bool close(CameraStateMachine* const csm) override final;
  };

  //!
  //! \brief Capture state class.
  //!
  class Capture : public State {
   public:
    explicit Capture() = default;
    virtual ~Capture() override final = default;

    virtual bool pause(CameraStateMachine* const csm) override final;
    virtual bool stop(CameraStateMachine* const csm) override final;
  };

  //!
  //! \brief Pause state class.
  //!
  class Pause : public State {
   public:
    explicit Pause() = default;
    virtual ~Pause() override final = default;

    virtual bool resume(CameraStateMachine* const csm) override final;
    virtual bool stop(CameraStateMachine* const csm) override final;
  };

  //! Current state.
  State* m_state;

  bool m_isReady = false;
  bool m_isCapture = false;
  bool m_isPause = false;
};

}  // namespace capture

#endif
