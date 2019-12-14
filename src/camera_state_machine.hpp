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
  CameraStateMachine& operator=(const CameraStateMachine&) = delete;
  //! NonMovable.
  CameraStateMachine(CameraStateMachine&&) = delete;
  CameraStateMachine& operator=(CameraStateMachine&&) = delete;

  //! State types.
  enum class State { OFF, READY, CAPTURE, PAUSE };

  void open();
  void start();
  void pause();
  void resume();
  void stop();
  void close();

  //!
  //! \brief Get current state.
  //! \return State type.
  //!
  [[nodiscard]] State state() const noexcept;

 protected:
  [[nodiscard]] virtual bool onOpen() = 0;
  [[nodiscard]] virtual bool onStart() = 0;
  [[nodiscard]] virtual bool onPause() = 0;
  [[nodiscard]] virtual bool onResume() = 0;
  [[nodiscard]] virtual bool onStop() = 0;
  [[nodiscard]] virtual bool onClose() = 0;

 private:
  //!
  //! \brief Base state class.
  //!
  class BaseState {
   public:
    virtual ~BaseState() = default;

    //! NonCopyable.
    BaseState(const BaseState&) = delete;
    BaseState& operator=(const BaseState&) = delete;
    //! NonMovable.
    BaseState(BaseState&&) = delete;
    BaseState& operator=(BaseState&&) = delete;

    virtual void open();
    virtual void start();
    virtual void pause();
    virtual void resume();
    virtual void stop();
    virtual void close();

   protected:
    //!
    //! \brief State class constructor.
    //! \param[in] csm Context CameraStateMachine.
    //!
    explicit BaseState(CameraStateMachine* csm);

    //!
    //! \brief Get context.
    //! \return CameraStateMachine pointer.
    //!
    [[nodiscard]] CameraStateMachine* context() const noexcept;

   private:
    //! Context CameraStateMachine.
    CameraStateMachine* m_csm = nullptr;
  };

  //!
  //! \brief Off state class.
  //!
  class Off : public BaseState {
   public:
    explicit Off(CameraStateMachine* csm);

    void open() final;
  };

  //!
  //! \brief Ready state class.
  //!
  class Ready : public BaseState {
   public:
    explicit Ready(CameraStateMachine* csm);

    void start() final;
    void close() final;
  };

  //!
  //! \brief Capture state class.
  //!
  class Capture : public BaseState {
   public:
    explicit Capture(CameraStateMachine* csm);

    void pause() final;
    void stop() final;
  };

  //!
  //! \brief Pause state class.
  //!
  class Pause : public BaseState {
   public:
    explicit Pause(CameraStateMachine* csm);

    void resume() final;
    void stop() final;
  };

  //!
  //! \brief Change current state.
  //! \param state New state.
  //!
  void change(State state);

  //! Array of state instances.
  std::array<BaseState*, 4> m_s{nullptr};
  //! Current state.
  State m_state = State::OFF;
};

}  // namespace capture

#endif
