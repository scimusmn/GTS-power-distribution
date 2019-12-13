import React from 'react';
import propTypes from 'prop-types';
import withSerialCommunication from '../Arduino/arduino-base/ReactSerial/SerialHOC';

class Clock extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      clockDisplay: 0,
    };

    this.onData = this.onData.bind(this);
  }

  componentDidMount() {
    const { setOnDataCallback } = this.props;
    setOnDataCallback(this.onData);
  }

  onData(data) {
    if (data.message === 'clock') {
      this.setState({ clockDisplay: data.value });
    }
  }

  render() {
    const { clockDisplay } = this.state;
    return (
      <pre className="clockDisplay">
        <code>{ clockDisplay }</code>
      </pre>
    );
  }
}

Clock.propTypes = {
  setOnDataCallback: propTypes.func.isRequired,
};

const ClockWithSerial = withSerialCommunication(Clock);

export default ClockWithSerial;
