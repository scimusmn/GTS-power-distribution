import React, { Component, Fragment } from 'react';
import { Container } from 'reactstrap';
import propTypes from 'prop-types';
import { ARDUINO_READY, WAKE_ARDUINO } from '../Arduino/arduino-base/ReactSerial/arduinoConstants';
import IPC from '../Arduino/arduino-base/ReactSerial/IPCMessages';
import withSerialCommunication from '../Arduino/arduino-base/ReactSerial/SerialHOC';

//
// Serve the app from a subdirectory in production if needed.
//

class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      handshake: false,
      pingArduinoStatus: false,
      refreshPortCount: 0,
      clockHour: 0,
      clockMin: 0,
      amOrPm: 'AM',
    };

    this.onSerialData = this.onSerialData.bind(this);
    this.pingArduino = this.pingArduino.bind(this);
    this.refreshPorts = this.refreshPorts.bind(this);
  }

  componentDidMount() {
    const { setOnDataCallback } = this.props;
    setOnDataCallback(this.onSerialData);
    document.addEventListener('keydown', this.handleReset);
    this.pingArduino();
  }

  onSerialData(data) {
    let amOrPm = 'AM';
    let hour;
    let min;

    const {
      handshake,
    } = this.state;

    if (data.message === ARDUINO_READY.message) {
      if (!handshake) this.setState({ handshake: true });

      this.setState({
        pingArduinoStatus: false,
        refreshPortCount: 0,
      });
    }

    if (handshake) {
      if (data.message === 'clock') {
        min = data.value % 100;
        hour = (data.value - min) / 100;
        if (hour > 11 && hour < 24) {
          amOrPm = 'PM';
        }
        if (hour > 12) {
          hour -= 12;
        }
        this.setState({ clockHour: hour, clockMin: min, amOrPm });
      }
    }
  }

  pingArduino() {
    const { sendData } = this.props;
    const { pingArduinoStatus } = this.state;

    if (pingArduinoStatus) this.refreshPorts();
    this.setState({ pingArduinoStatus: true });
    sendData(JSON.stringify(WAKE_ARDUINO));

    setTimeout(() => { this.pingArduino(); }, 5000);
  }

  refreshPorts() {
    const { sendData, startIpcCommunication, stopIpcCommunication } = this.props;
    const { refreshPortCount } = this.state;

    if (refreshPortCount === 2) {
      this.setState({ handshake: false });

      console.log('sending RESET-PORT');
      sendData(IPC.RESET_PORTS_COMMAND);
      console.log('restarting ipcCommunication...');

      stopIpcCommunication();
      startIpcCommunication();
    }

    this.setState(prevState => ({ refreshPortCount: prevState.refreshPortCount + 1 }));
  }

  render() {
    const {
      clockHour, clockMin, amOrPm, handshake,
    } = this.state;
    let isZero = ':';

    if (!handshake) {
      return (
        <Container>
          <p> no handshake </p>
        </Container>
      );
    }

    if (clockMin < 10) {
      isZero = ':0';
    }

    return (
      <Fragment>
        <Container>
          <h1>
            {clockHour}
            {isZero}
            {clockMin}
            {amOrPm}
          </h1>
        </Container>
      </Fragment>
    );
  }
}

App.propTypes = {
  sendData: propTypes.func.isRequired,
  setOnDataCallback: propTypes.func.isRequired,
  startIpcCommunication: propTypes.func.isRequired,
  stopIpcCommunication: propTypes.func.isRequired,
};

const AppWithSerialCommunication = withSerialCommunication(App);
export default AppWithSerialCommunication;
