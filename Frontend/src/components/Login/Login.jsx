import { useMutation, useQueryClient } from '@tanstack/react-query'
import { useForm } from 'react-hook-form'
import axios from 'axios'

export default function Login() {
	const { register, handleSubmit, errors } = useForm({
		mode: 'onChange'
	})
	const createEmployee = async data => {
		const { data: response } = await axios.post(
			'http://192.168.0.105:8080/register',
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
		localStorage.setItem('name', data.name)
		mutate(JSON.stringify(data))
	}
	return (
		<>
			<form onSubmit={handleSubmit(onSubmit)} method='POST'>
				<div>
					{localStorage.getItem('name') == null
						? 'Введите свой логин:'
						: `Вы зашли под именем: ${localStorage.getItem('name')}`}
				</div>
				<input
					className='border mr-2 w-full mb-2 py-1 px-2 rounded'
					{...register('name')}
					type='text'
					placeholder={localStorage.getItem('name')}
				/>
				<button className=' p-2 rounded bg-black text-white mr-2' type='submit'>
					Сохранить
				</button>
				<button
					onClick={() => localStorage.removeItem('name')}
					className=' p-2 rounded bg-black text-white'
					type='button'
				>
					Удалить
				</button>
			</form>
		</>
	)
}
