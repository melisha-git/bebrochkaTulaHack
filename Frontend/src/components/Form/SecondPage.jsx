import Image from 'next/image'
import Link from 'next/link'
import { useDispatch } from 'react-redux'

import { setPage } from '@/store/slice/countSlice'
import { setCategory } from '@/store/slice/idSlice'
import { data } from './data'

export default function SecondPage() {
	const dispatch = useDispatch()
	const replace = name => {
		dispatch(setCategory(name))
		dispatch(setPage(4))
	}
	return (
		<>
			<Image src='/images/duckCup.gif' width={250} height={250} />
			<div className=' text-lg mb-3 text-center'>
				Отлично, а теперь какие места для отдыха?
			</div>
			<div className='flex gap-3 flex-wrap w-4/5 justify-center'>
				{data.map((item, id) => (
					<Link key={id} href='/place'>
						<button
							onClick={() => replace(item.slug)}
							className=' bg-slate-200 p-2 rounded-md hover:bg-black hover:text-white cursor-pointer'
						>
							{item.name}
						</button>
					</Link>
				))}
			</div>
		</>
	)
}
