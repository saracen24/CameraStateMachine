//!
//! \file camera_state_machine.hpp.
//! \brief Camera state machine.
//! \author Aiz (c).
//! \date 2019.
//!

#pragma once
#ifndef CAMERA_STATE_MACHINE_HPP
#define CAMERA_STATE_MACHINE_HPP

#include <array>

namespace capture {

//!
//! \brief CameraStateMachine class.
//!
class CameraStateMachine {
 public:
  explicit CameraStateMachine();
  virtual ~CameraStateMachine();

  //! NonCopyable.
  CameraStateMachine(const CameraStateMachine&) = delete;
  CameraStateMachine(CameraStateMachine&&) = delete;
  CameraStateMachine& operator=(const CameraStateMachine&) = delete;
  CameraStateMachine& operator=(CameraStateMachine&&) = delete;

  void open();
  void start();
  void pause();
  void resume();
  void stop();
  void close();

  enum class StateType { OFF, READY, CAPTURE, PAUSE };

  [[nodiscard]] StateType state() const noexcept;

 protected:
  [[nodiscard]] virtual bool onOpen() = 0;
  [[nodiscard]] virtual bool onStart() = 0;
  [[nodiscard]] virtual bool onPause() = 0;
  [[nodiscard]] virtual bool onResume() = 0;
  [[nodiscard]] virtual bool onStop() = 0;
  [[nodiscard]] virtual bool onClose() = 0;

 private:
  //!
  //! \brief State base class.
  //!
  class State {
   public:
    virtual ~State() = default;

    virtual void open();
    virtual void start();
    virtual void pause();
    virtual void resume();
    virtual void stop();
    virtual void close();

   protected:
    explicit State(CameraStateMachine* context);

    CameraStateMachine* m_csm = nullptr;
  };

  //!
  //! \brief Change current state.
  //! \param[in] state New state.
  //!
  void change(StateType state);

  //!
  //! \brief Off state class.
  //!
  class Off : public State {
   public:
    explicit Off(CameraStateMachine* csm);
    ~Off() final = default;

    void open() final;
  };

  //!
  //! \brief Ready state class.
  //!
  class Ready : public State {
   public:
    explicit Ready(CameraStateMachine* csm);
    ~Ready() final = default;

    void start() final;
    void close() final;
  };

  //!
  //! \brief Capture state class.
  //!
  class Capture : public State {
   public:
    explicit Capture(CameraStateMachine* csm);
    ~Capture() final = default;

    void pause() final;
    void stop() final;
  };

  //!
  //! \brief Pause state class.
  //!
  class Pause : public State {
   public:
    explicit Pause(CameraStateMachine* csm);
    ~Pause() final = default;

    void resume() final;
    void stop() final;
  };

  std::array<State*, 4> m_s{nullptr};
  StateType m_state = StateType::OFF;
};

}  // namespace capture

#endif
