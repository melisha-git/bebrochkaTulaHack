import Link from 'next/link'

export default function FourOhFour() {
	return (
		<div className=' text-center mt-4'>
			<h1 className=' text-2xl mb-5'>Ошибка страница не найдена</h1>
			<Link href='/place' className='border-2 p-2 rounded-md'>
				Вернуться обратно
			</Link>
		</div>
	)
}
