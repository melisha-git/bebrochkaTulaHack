import Image from 'next/image'
import { useDispatch } from 'react-redux'
import { increment } from '@/store/slice/countSlice'

export default function FirstPage() {
	const dispatch = useDispatch()
	return (
		<>
			<Image src='/images/duckBoss.gif' width={250} height={250} priority />
			<div className=' text-lg mb-3 text-center'>
				Какой тип отдыха тебе нравится больше?
			</div>
			<div className='flex gap-3'>
				<button
					onClick={() => dispatch(increment())}
					className=' bg-slate-200 p-2 rounded-md hover:bg-black hover:text-white cursor-pointer'
				>
					Активный отдых
				</button>
				<button
					onClick={() => dispatch(increment())}
					className=' bg-slate-200 p-2 rounded-md hover:bg-black hover:text-white cursor-pointer'
				>
					Пассивный отдых
				</button>
			</div>
		</>
	)
}
