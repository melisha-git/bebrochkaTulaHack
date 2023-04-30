import { useSelector } from 'react-redux'

import FirstPage from './FirstPage'
import SecondPage from './SecondPage'

export default function Form() {
	const count = useSelector(state => state.counterReducer.value)
	return (
		<div className=' bg-white text-black flex flex-col justify-center items-center h-screen'>
			{count === 0 ? <FirstPage /> : <SecondPage />}
		</div>
	)
}
