import React, { useState } from 'react'
import ReactDOM from 'react-dom'

const Display = props => <div>{props.value}</div>

const Button = (props) => (
	<button onClick={props.handleClick}>
		{props.text}
	</button>
)

const App = () => {
	const [value, setValue] = useState(10)

	const setToValue = (newvalue) => {
		setValue(newvalue)
	}

	return (
		<div>
			<Display value={value} />
			<Button handleClick={() => setToValue(1000)} text="thousand" />
			<Button handleClick={() => setToValue(0)} text="reset" />
			<Button handleClick={() => setToValue(value + 1)} text="increment" />
		</div>
	)
}

ReactDOM.render(
	<App />,
	document.getElementById('root')
)
