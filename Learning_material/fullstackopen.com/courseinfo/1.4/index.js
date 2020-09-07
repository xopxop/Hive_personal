import React from 'react'
import ReactDOM from 'react-dom'

const Header = (props) => {
	console.log(props)
	return (
		<h1>{props.course}</h1>
	)
}

const Part = (props) => {
	return (
		<div>
			<p>
				{props.part} {props.exercises}
			</p>
		</div>
	)
}

const Content = (props) => {
	console.log(props)
	return (
		<div>
			<Part part={props.parts[0].name} exercises={props.parts[0].exercises}/>
			<Part part={props.parts[1].name} exercises={props.parts[1].exercises}/>
			<Part part={props.parts[2].name} exercises={props.parts[2].exercises}/>
		</div>
	)
}

const Total = (props) => {
	return (
		<div>
			<p>NUmber of excercises {props.parts[0].exercises + props.parts[1].exercises + props.parts[2].exercises}</p>
		</div>
	)
}

const App = () => {
	const course = 'Half Stack application development'
	const parts = [
		{
			name: 'Fundamentals of React',
			exercises: 10
		},
		{
			name: 'Using props to pass data',
			exercises: 7
		},
		{
			name: 'State of a compoment',
			exercises: 14
		}
	]

	return (
		<div>
			<Header course={course} />
			<Content parts={parts} />
			<Total parts={parts}/>
		</div>
	)
}

ReactDOM.render(<App />, document.getElementById('root'))
