import { useMutation, useQueryClient } from '@tanstack/react-query'
import { useSelector, useDispatch } from 'react-redux'
import { useForm } from 'react-hook-form'
import axios from 'axios'

export default function Invite() {
	const place = useSelector(state => state.idReducer.place)
	const { register, handleSubmit, reset } = useForm({
		mode: 'onChange'
	})
	const createEmployee = async data => {
		const { data: response } = await axios.post(
			'http://192.168.0.105:8080/calendar',
			data
		)
		return response.data
	}
	const queryClient = useQueryClient()
	const { mutate, isLoading } = useMutation(createEmployee, {
		onSuccess: data => {
			console.log(data)
			const message = 'success'
			console.log(message)
		},
		onError: () => {
			console.log('there was an error')
		},
		onSettled: () => {
			queryClient.invalidateQueries('create')
		}
	})
	const onSubmit = data => {
		const employee = {
			...data,
			...place,
			user_name: localStorage.getItem('name')
		}
		console.log(place)
		console.log(JSON.stringify(employee))
		mutate(JSON.stringify(employee))
		reset()
	}
	if (localStorage.getItem('name') == null)
		return <div className=' text-center'>Нужно войти в систему</div>

	return (
		<>
			<form onSubmit={handleSubmit(onSubmit)} method='POST'>
				<div>Кого хотите пригласить?</div>
				<input
					className='border mr-2 w-full mb-2 py-1 px-2 rounded'
					{...register('friend_name')}
					type='text'
					placeholder='Gosha'
				/>
				<input
					className='border mr-2 w-full mb-2 py-1 px-2 rounded'
					{...register('date')}
					type='text'
					placeholder='30.04.2023'
				/>
				<input
					className='border mr-2 w-full mb-2 py-1 px-2 rounded'
					{...register('time')}
					type='12'
					placeholder='12:30'
				/>
				<button className=' p-2 rounded bg-black text-white mr-2' type='submit'>
					Отправить
				</button>
			</form>
		</>
	)
}
